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
 int byleng (char*,int) ; 
 int /*<<< orphan*/  ldchar (char*,int,char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  rupshift (char*) ; 

int main(void)
{
	char t1[] = "abc  def  ghi  ";
	          /* 123456789012345 */
	char buf[50];
	int k;

	printf("t1: _%s_\n", t1);
	rupshift(t1);
	printf("t1: _%s_\n", t1);

	k = 2;
	ldchar(t1, k, buf);
	printf("byleng(t1, %d): %d, ldchar: _%s_\n", k, byleng(t1, k), buf);
	k = 5;
	ldchar(t1, k, buf);
	printf("byleng(t1, %d): %d, ldchar: _%s_\n", k, byleng(t1, k), buf);
	k = 9;
	ldchar(t1, k, buf);
	printf("byleng(t1, %d): %d, ldchar: _%s_\n", k, byleng(t1, k), buf);
	k = 15;
	ldchar(t1, k, buf);
	printf("byleng(t1, %d): %d, ldchar: _%s_\n", k, byleng(t1, k), buf);


	return 0;
}