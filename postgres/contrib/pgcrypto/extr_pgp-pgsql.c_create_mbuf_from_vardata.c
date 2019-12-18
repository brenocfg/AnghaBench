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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/  MBuf ;

/* Variables and functions */
 scalar_t__ VARDATA_ANY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VARSIZE_ANY_EXHDR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mbuf_create_from_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static MBuf *
create_mbuf_from_vardata(text *data)
{
	return mbuf_create_from_data((uint8 *) VARDATA_ANY(data),
								 VARSIZE_ANY_EXHDR(data));
}