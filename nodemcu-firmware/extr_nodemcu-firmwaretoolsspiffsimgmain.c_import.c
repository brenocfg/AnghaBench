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
 int /*<<< orphan*/  O_RDONLY ; 
 int SPIFFS_CREAT ; 
 int SPIFFS_TRUNC ; 
 int SPIFFS_WRONLY ; 
 scalar_t__ SPIFFS_close (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ SPIFFS_open (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ SPIFFS_write (int /*<<< orphan*/ *,scalar_t__,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  fs ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read (int,char*,int) ; 

__attribute__((used)) static void import (char *src, char *dst)
{
  int fd = open (src, O_RDONLY);
  if (fd < 0)
    die (src);

  spiffs_file fh = SPIFFS_open (&fs, dst, SPIFFS_CREAT | SPIFFS_TRUNC | SPIFFS_WRONLY, 0);
  if (fh < 0)
    die ("spiffs_open");

  char buff[16384];
  s32_t n;
  while ((n = read (fd, buff, sizeof (buff))) > 0)
    if (SPIFFS_write (&fs, fh, buff, n) < 0)
      die ("spiffs_write");

  if (SPIFFS_close (&fs, fh) < 0)
    die("spiffs_close");
  close (fd);
}