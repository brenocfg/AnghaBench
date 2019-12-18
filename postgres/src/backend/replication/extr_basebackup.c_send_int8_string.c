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
typedef  int /*<<< orphan*/  int64 ;
typedef  int /*<<< orphan*/  StringInfoData ;

/* Variables and functions */
 char* INT64_FORMAT ; 
 int /*<<< orphan*/  pq_sendbytes (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pq_sendint32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void
send_int8_string(StringInfoData *buf, int64 intval)
{
	char		is[32];

	sprintf(is, INT64_FORMAT, intval);
	pq_sendint32(buf, strlen(is));
	pq_sendbytes(buf, is, strlen(is));
}