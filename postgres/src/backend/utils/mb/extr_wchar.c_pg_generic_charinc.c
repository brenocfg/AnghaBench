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
typedef  int (* mbverifier ) (unsigned char*,int) ;
struct TYPE_2__ {int (* mbverify ) (unsigned char*,int) ;} ;

/* Variables and functions */
 size_t GetDatabaseEncoding () ; 
 TYPE_1__* pg_wchar_table ; 
 int stub1 (unsigned char*,int) ; 

__attribute__((used)) static bool
pg_generic_charinc(unsigned char *charptr, int len)
{
	unsigned char *lastbyte = charptr + len - 1;
	mbverifier	mbverify;

	/* We can just invoke the character verifier directly. */
	mbverify = pg_wchar_table[GetDatabaseEncoding()].mbverify;

	while (*lastbyte < (unsigned char) 255)
	{
		(*lastbyte)++;
		if ((*mbverify) (charptr, len) == len)
			return true;
	}

	return false;
}