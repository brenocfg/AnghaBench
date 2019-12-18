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
typedef  int /*<<< orphan*/  v2 ;
struct pevaluator {int /*<<< orphan*/  csw; } ;
typedef  int /*<<< orphan*/  res ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PEV_ERROR1 (struct pevaluator*,char*,int /*<<< orphan*/ ) ; 
 int PEV_MAX_LEN ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  pev_pop_val (struct pevaluator*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pev_push (struct pevaluator*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sw_read_mem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static BOOL  pev_deref(struct pevaluator* pev)
{
    char        res[PEV_MAX_LEN];
    DWORD_PTR   v1, v2;

    if (!pev_pop_val(pev, &v1)) return FALSE;
    if (!sw_read_mem(pev->csw, v1, &v2, sizeof(v2)))
        return PEV_ERROR1(pev, "deref: cannot read mem at %lx\n", v1);
    snprintf(res, sizeof(res), "%ld", v2);
    pev_push(pev, res);
    return TRUE;
}