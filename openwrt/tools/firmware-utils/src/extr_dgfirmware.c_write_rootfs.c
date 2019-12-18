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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ROOTFS_SIZE ; 
 int ROOTFS_START ; 
 char* app_name ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ fwrite (unsigned char*,int,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stderr ; 

void write_rootfs(unsigned char* img, const char *fname)
{
  FILE *fp;

  fp = fopen(fname, "wb");
  if (fp == NULL) {
    perror(app_name);
    exit(-1);
  }
  
  if (fwrite(img+ROOTFS_START, 1, ROOTFS_SIZE, fp) != ROOTFS_SIZE) {
    fprintf(stderr, "%s: can't write image file\n", app_name);
    fclose(fp);
    exit(-1);
  }
}