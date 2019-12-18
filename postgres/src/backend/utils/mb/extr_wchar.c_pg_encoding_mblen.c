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
struct TYPE_2__ {int (* mblen ) (unsigned char const*) ;} ;

/* Variables and functions */
 size_t PG_SQL_ASCII ; 
 scalar_t__ PG_VALID_ENCODING (int) ; 
 TYPE_1__* pg_wchar_table ; 
 int stub1 (unsigned char const*) ; 
 int stub2 (unsigned char const*) ; 

int
pg_encoding_mblen(int encoding, const char *mbstr)
{
	return (PG_VALID_ENCODING(encoding) ?
			pg_wchar_table[encoding].mblen((const unsigned char *) mbstr) :
			pg_wchar_table[PG_SQL_ASCII].mblen((const unsigned char *) mbstr));
}