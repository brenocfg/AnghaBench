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
typedef  scalar_t__ spiffs_file ;
typedef  int /*<<< orphan*/  s32_t ;
typedef  int /*<<< orphan*/  buff ;

/* Variables and functions */
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  SPIFFS_RDONLY ; 
 int /*<<< orphan*/  SPIFFS_close (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ SPIFFS_open (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPIFFS_read (int /*<<< orphan*/ *,scalar_t__,char*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  fs ; 
 int open (char*,int,int) ; 
 scalar_t__ write (int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void export (char *src, char *dst)
{
  spiffs_file fh = SPIFFS_open (&fs, src, SPIFFS_RDONLY, 0);
  if (fh < 0)
    die ("spiffs_open");

  int fd = open (dst, O_CREAT | O_TRUNC | O_WRONLY, 0664);
  if (fd < 0)
    die (dst);

  char buff[512];
  s32_t n;
  while ((n = SPIFFS_read (&fs, fh, buff, sizeof (buff))) > 0)
    if (write (fd, buff, n) < 0)
      die ("write");

  SPIFFS_close (&fs, fh);
  close (fd);
}