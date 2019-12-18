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
typedef  int /*<<< orphan*/  gzFile ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int BUFLENW ; 
 scalar_t__ Z_OK ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fwrite (char*,int,unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ gzclose (int /*<<< orphan*/ ) ; 
 char* gzerror (int /*<<< orphan*/ ,int*) ; 
 int gzread (int /*<<< orphan*/ ,char*,int) ; 

void gz_uncompress(gzFile in, FILE   *out)
{
    char buf[BUFLENW];
    int len;
    int err;

    for (;;) {
        len = gzread(in, buf, sizeof(buf));
        if (len < 0) error (gzerror(in, &err));
        if (len == 0) break;

        if ((int)fwrite(buf, 1, (unsigned)len, out) != len) {
            error("failed fwrite");
        }
    }
    if (fclose(out)) error("failed fclose");

    if (gzclose(in) != Z_OK) error("failed gzclose");
}