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
typedef  int uint8 ;
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int XLHL_KEYS_UPDATED ; 
 int XLHL_XMAX_EXCL_LOCK ; 
 int XLHL_XMAX_IS_MULTI ; 
 int XLHL_XMAX_KEYSHR_LOCK ; 
 int XLHL_XMAX_LOCK_ONLY ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
out_infobits(StringInfo buf, uint8 infobits)
{
	if (infobits & XLHL_XMAX_IS_MULTI)
		appendStringInfoString(buf, "IS_MULTI ");
	if (infobits & XLHL_XMAX_LOCK_ONLY)
		appendStringInfoString(buf, "LOCK_ONLY ");
	if (infobits & XLHL_XMAX_EXCL_LOCK)
		appendStringInfoString(buf, "EXCL_LOCK ");
	if (infobits & XLHL_XMAX_KEYSHR_LOCK)
		appendStringInfoString(buf, "KEYSHR_LOCK ");
	if (infobits & XLHL_KEYS_UPDATED)
		appendStringInfoString(buf, "KEYS_UPDATED ");
}