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
typedef  int /*<<< orphan*/  tmp ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSPC ; 
 int /*<<< orphan*/  SET_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int,int,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char*) ; 

__attribute__((used)) static char *inet_ntop4 (const unsigned char *src, char *dst, size_t size)
{
  size_t len;
  char tmp[sizeof "255.255.255.255"];

  tmp[0] = '\0';
  (void)snprintf(tmp, sizeof(tmp), "%d.%d.%d.%d",
          ((int)((unsigned char)src[3])) & 0xff,
          ((int)((unsigned char)src[2])) & 0xff,
          ((int)((unsigned char)src[1])) & 0xff,
          ((int)((unsigned char)src[0])) & 0xff);

  len = strlen(tmp);
  if(len == 0 || len >= size)
  {
    SET_ERRNO(ENOSPC);
    return (NULL);
  }
  strcpy(dst, tmp);
  return dst;
}