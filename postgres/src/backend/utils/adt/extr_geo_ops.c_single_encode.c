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
typedef  int /*<<< orphan*/  float8 ;
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 char* float8out_internal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfree (char*) ; 

__attribute__((used)) static void
single_encode(float8 x, StringInfo str)
{
	char	   *xstr = float8out_internal(x);

	appendStringInfoString(str, xstr);
	pfree(xstr);
}