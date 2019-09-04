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
typedef  int /*<<< orphan*/  grub_uint8_t ;
typedef  int /*<<< orphan*/  grub_uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  grub_be_to_cpu16 (int /*<<< orphan*/ ) ; 
 char* grub_malloc (int) ; 
 char* grub_utf16_to_utf8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static char *
grub_iso9660_convert_string (grub_uint16_t *us, int len)
{
  char *p;
  int i;

  p = grub_malloc (len * 4 + 1);
  if (! p)
    return p;

  for (i=0; i<len; i++)
    us[i] = grub_be_to_cpu16 (us[i]);

  *grub_utf16_to_utf8 ((grub_uint8_t *) p, us, len) = '\0';

  return p;
}