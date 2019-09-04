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
struct RangeList {int dummy; } ;
struct Range {int begin; scalar_t__ end; } ;
typedef  scalar_t__ errno_t ;
typedef  int /*<<< orphan*/  address ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  LOG (int /*<<< orphan*/ ,char*,char const*,unsigned int,unsigned int,int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 scalar_t__ fopen_s (int /*<<< orphan*/ **,char const*,char*) ; 
 int getc (int /*<<< orphan*/ *) ; 
 scalar_t__ ispunct (int) ; 
 scalar_t__ isspace (int) ; 
 int /*<<< orphan*/  perror (char const*) ; 
 struct Range range_parse_ipv4 (char*,unsigned int*,unsigned int) ; 
 int /*<<< orphan*/  rangelist_add_range (struct RangeList*,int,scalar_t__) ; 
 int /*<<< orphan*/  rangelist_sort (struct RangeList*) ; 

__attribute__((used)) static void
ranges_from_file(struct RangeList *ranges, const char *filename)
{
    FILE *fp;
    errno_t err;
    unsigned line_number = 0;

    err = fopen_s(&fp, filename, "rt");
    if (err) {
        perror(filename);
        exit(1); /* HARD EXIT: because if it's an exclusion file, we don't
                  * want to continue. We don't want ANY chance of
                  * accidentally scanning somebody */
    }

    while (!feof(fp)) {
        int c = '\n';

        /* remove leading whitespace */
        while (!feof(fp)) {
            c = getc(fp);
            line_number += (c == '\n');
            if (!isspace(c&0xFF))
                break;
        }

        /* If this is a punctuation, like '#', then it's a comment */
        if (ispunct(c&0xFF)) {
            while (!feof(fp)) {
                c = getc(fp);
                line_number += (c == '\n');
                if (c == '\n') {
                    break;
                }
            }
            /* Loop back to the begining state at the start of a line */
            continue;
        }

        if (c == '\n') {
            continue;
        }

        /*
         * Read in a single entry
         */
        if (!feof(fp)) {
            char address[64];
            size_t i;
            struct Range range;
            unsigned offset = 0;


            /* Grab all bytes until the next space or comma */
            address[0] = (char)c;
            i = 1;
            while (!feof(fp)) {
                c = getc(fp);
                if (c == EOF)
                    break;
                line_number += (c == '\n');
                if (isspace(c&0xFF) || c == ',') {
                    break;
                }
                if (i+1 >= sizeof(address)) {
                    LOG(0, "%s:%u:%u: bad address spec: \"%.*s\"\n",
                            filename, line_number, offset, (int)i, address);
                    exit(1);
                } else
                    address[i] = (char)c;
                i++;
            }
            address[i] = '\0';

            /* parse the address range */
            range = range_parse_ipv4(address, &offset, (unsigned)i);
            if (range.begin == 0xFFFFFFFF && range.end == 0) {
                LOG(0, "%s:%u:%u: bad range spec: \"%.*s\"\n",
                        filename, line_number, offset, (int)i, address);
                exit(1);
            } else {
                rangelist_add_range(ranges, range.begin, range.end);
            }
        }
    }

    fclose(fp);

    /* Target list must be sorted every time it's been changed, 
     * before it can be used */
    rangelist_sort(ranges);
}