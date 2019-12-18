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
 char* MD5FileChunk (char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

char *MD5File(const char *filename, char *buf)
{
  return (MD5FileChunk(filename, buf, 0, 0));
}