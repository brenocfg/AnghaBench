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
struct PcapFile {unsigned int linktype; int /*<<< orphan*/  byte_order; int /*<<< orphan*/ * fp; int /*<<< orphan*/  filename; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CAPFILE_LITTLEENDIAN ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (struct PcapFile*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char const*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char const*) ; 
 int /*<<< orphan*/  stderr ; 

struct PcapFile *pcapfile_openwrite(const char *capfilename, unsigned linktype)
{
    char buf[] =
            "\xd4\xc3\xb2\xa1\x02\x00\x04\x00"
            "\x00\x00\x00\x00\x00\x00\x00\x00"
            "\xff\xff\x00\x00\x69\x00\x00\x00";
    FILE *fp;

    buf[20] = (char)(linktype>>0);
    buf[21] = (char)(linktype>>8);


    fp = fopen(capfilename, "wb");
    if (fp == NULL) {
        fprintf(stderr, "Could not open capture file\n");
        perror(capfilename);
        return 0;
    }


    if (fwrite(buf, 1, 24, fp) != 24) {
        fprintf(stderr, "Could not write capture file header\n");
        perror(capfilename);
        fclose(fp);
        return 0;
    }

    {
        struct PcapFile *capfile = 0;
        capfile = (struct PcapFile*)malloc(sizeof(*capfile));
        if (capfile == NULL)
            exit(1);
        memset(capfile,0,sizeof(*capfile));

        snprintf(capfile->filename, sizeof(capfile->filename),
                 "%s", capfilename);

        capfile->fp = fp;
        capfile->byte_order = CAPFILE_LITTLEENDIAN;
        capfile->linktype = linktype;
        return capfile;
    }

}