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

/* Variables and functions */
 char* MD5File (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 int strlen (char*) ; 

int main(int argc, char *argv[])
{
  char *md5sum = NULL, buf[65];

  if (argc < 3) {
    fprintf(stderr, "USAGE: %s <correct MD5 sum> <file>\n", argv[0]);
    return -1;
  }

  if (strlen(argv[1]) != 32)
    fprintf(stderr, "WARNING: MD5 hash size is wrong.\n");

  md5sum = MD5File(argv[2], buf);
  if (!md5sum) {
    perror("Could not obtain MD5 sum");
    return -1;
  }

  if (!strcasecmp(md5sum, argv[1])) {
    fprintf(stderr, "%s: OK\n", argv[2]);
    return 0;
  } else {
    fprintf(stderr, "%s: FAILED.  Checksum is %s\n", argv[2], md5sum);
    return -1;
  }
}