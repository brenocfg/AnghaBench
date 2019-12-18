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
typedef  int /*<<< orphan*/  MD5_CTX ;

/* Variables and functions */
 char* MD5End (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  MD5Init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MD5Update (int /*<<< orphan*/ *,unsigned char*,unsigned int) ; 

char *MD5Data(const void *data, unsigned int len, char *buf)
{
  MD5_CTX ctx;

  MD5Init(&ctx);
  MD5Update(&ctx, (unsigned char *)data, len);
  return (MD5End(&ctx, buf));
}