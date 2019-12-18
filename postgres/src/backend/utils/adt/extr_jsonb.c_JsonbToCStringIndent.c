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
typedef  int /*<<< orphan*/  StringInfo ;
typedef  int /*<<< orphan*/  JsonbContainer ;

/* Variables and functions */
 char* JsonbToCStringWorker (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 

char *
JsonbToCStringIndent(StringInfo out, JsonbContainer *in, int estimated_len)
{
	return JsonbToCStringWorker(out, in, estimated_len, true);
}