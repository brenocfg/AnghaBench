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
struct PreprocessedInfo {int dummy; } ;
struct PcapFile {int dummy; } ;
typedef  int /*<<< orphan*/  px ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  pcapfile_close (struct PcapFile*) ; 
 unsigned int pcapfile_datalink (struct PcapFile*) ; 
 struct PcapFile* pcapfile_openread (char const*) ; 
 int pcapfile_readframe (struct PcapFile*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned char*,int) ; 
 unsigned int preprocess_frame (unsigned char*,unsigned int,unsigned int,struct PreprocessedInfo*) ; 
 int /*<<< orphan*/  stderr ; 

void
banner1_test(const char *filename)
{
    struct PcapFile *cap;
    unsigned link_type;

    cap = pcapfile_openread(filename);
    if (cap == NULL) {
        fprintf(stderr, "%s: can't open capture file\n", filename);
        return;
    }

    link_type = pcapfile_datalink(cap);

    for (;;) {
        int packets_read;
        unsigned secs;
        unsigned usecs;
        unsigned origlength;
        unsigned length;
        unsigned char px[65536];
        struct PreprocessedInfo parsed;
        unsigned x;


        packets_read = pcapfile_readframe(
                    cap,    /* capture dump file */
                    &secs, &usecs,
                    &origlength, &length,
                    px, sizeof(px));
        if (packets_read == 0)
            break;


        x = preprocess_frame(px, length, link_type, &parsed);
        if (x == 0)
            continue;

    }

    pcapfile_close(cap);
}