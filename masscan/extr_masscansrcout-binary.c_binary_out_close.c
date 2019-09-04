#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {size_t bytes_written; } ;
struct Output {TYPE_1__ rotate; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSEDPARM (struct Output*) ; 
 int /*<<< orphan*/  exit (int) ; 
 size_t fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  sprintf_s (char*,int,char*) ; 

__attribute__((used)) static void
binary_out_close(struct Output *out, FILE *fp)
{
    char firstrecord[2+'a'];
    size_t bytes_written;

    UNUSEDPARM(out);

    memset(firstrecord, 0, 2+'a');
    sprintf_s(firstrecord, 2+'a', "masscan/1.1");
    bytes_written = fwrite(firstrecord, 1, 2+'a', fp);
    if (bytes_written != 2+'a') {
        perror("output");
        exit(1);
    }
    out->rotate.bytes_written += bytes_written;
}