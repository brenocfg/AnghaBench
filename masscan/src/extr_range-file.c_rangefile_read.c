#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct RangeParser {int dummy; } ;
struct RangeList {int dummy; } ;
struct Range6List {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LOG (int,char*,char const*,unsigned int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int fopen_s (int /*<<< orphan*/ **,char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 size_t fread (unsigned char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char const*) ; 
 int /*<<< orphan*/  rangelist_add_range (struct RangeList*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  rangelist_sort (struct RangeList*) ; 
 struct RangeParser* rangeparse_create () ; 
 int /*<<< orphan*/  rangeparse_err (struct RangeParser*,unsigned long long*,unsigned long long*) ; 
 int rangeparse_next (struct RangeParser*,unsigned char const*,size_t*,int,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  stderr ; 

int
rangefile_read(const char *filename, struct RangeList *targets_ipv4, struct Range6List *targets_ipv6)
{
    struct RangeParser *p;
    unsigned char buf[65536];
    FILE *fp = NULL;
    int err;
    bool is_error = false;
    unsigned addr_count = 0;

    /*
     * Open the file containing IP addresses, which can potentially be
     * many megabytes in size
     */
    err = fopen_s(&fp, filename, "rb");
    if (err || fp == NULL) {
        perror(filename);
        exit(1);
    }

    /*
     * Create a parser for reading in the IP addresses using a state
     * machine parser
     */
    p = rangeparse_create();

    /*
     * Read in the data a block at a time, parsing according to the state
     * machine.
     */
    while (!is_error) {
        size_t count;
        size_t offset;

        count = fread(buf, 1, sizeof(buf), fp);
        if (count <= 0)
            break;

        offset = 0;
        while (offset < count) {
            int x;
            unsigned begin, end;

            x = rangeparse_next(p, buf, &offset, count, &begin, &end);
            if (x < 0) {
                unsigned long long line_number, char_number;
                rangeparse_err(p, &line_number, &char_number);
                fprintf(stderr, "%s:%llu:%llu: parse err\n", filename, line_number, char_number);
                is_error = true;
                break;
            } else if (x == 1) {
                rangelist_add_range(targets_ipv4, begin, end);
                addr_count++;
            } else if (x == 0) {
                if (offset < count)
                    fprintf(stderr, "[-] fail\n");
            }
        }
    }
    fclose(fp);

    /* In case the file doesn't end with a newline '\n', then artificially
     * add one to the end */
    if (!is_error) {
        int x;
        size_t offset = 0;
        unsigned begin, end;
        x = rangeparse_next(p, (const unsigned char *)"\n", &offset, 1, &begin, &end);
        if (x < 0) {
            unsigned long long line_number, char_number;
            rangeparse_err(p, &line_number, &char_number);
            fprintf(stderr, "%s:%llu:%llu: parse err\n", filename, line_number, char_number);
            is_error = true;
        } else if (x == 1) {
            rangelist_add_range(targets_ipv4, begin, end);
            addr_count++;
        }
    }

    LOG(1, "[+] %s: %u addresses read\n", filename, addr_count);

    /* Target list must be sorted every time it's been changed, 
     * before it can be used */
    rangelist_sort(targets_ipv4);

    if (is_error)
        return -1;  /* fail */
    else
        return 0; /* success*/
}