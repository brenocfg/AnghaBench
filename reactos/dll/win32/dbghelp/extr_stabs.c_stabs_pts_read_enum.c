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
struct symt_enum {int dummy; } ;
struct ParseTypedefData {char* ptr; int idx; scalar_t__ buf; int /*<<< orphan*/  module; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTS_ABORTIF (struct ParseTypedefData*,int) ; 
 int stabs_pts_read_id (struct ParseTypedefData*) ; 
 int stabs_pts_read_number (struct ParseTypedefData*,long*) ; 
 int /*<<< orphan*/  symt_add_enum_element (int /*<<< orphan*/ ,struct symt_enum*,scalar_t__,long) ; 

__attribute__((used)) static inline int stabs_pts_read_enum(struct ParseTypedefData* ptd, 
                                      struct symt_enum* edt)
{
    long        value;
    int		idx;

    while (*ptd->ptr != ';')
    {
	idx = ptd->idx;
	PTS_ABORTIF(ptd, stabs_pts_read_id(ptd) == -1);
	PTS_ABORTIF(ptd, stabs_pts_read_number(ptd, &value) == -1);
	PTS_ABORTIF(ptd, *ptd->ptr++ != ',');
	symt_add_enum_element(ptd->module, edt, ptd->buf + idx, value);
	ptd->idx = idx;
    }
    ptd->ptr++;
    return 0;
}