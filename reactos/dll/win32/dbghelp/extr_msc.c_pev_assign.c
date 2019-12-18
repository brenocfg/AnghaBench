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
struct pevaluator {int dummy; } ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PEV_ERROR1 (struct pevaluator*,char*,char*) ; 
 int PEV_MAX_LEN ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  pev_pop (struct pevaluator*,char*) ; 
 int /*<<< orphan*/  pev_pop_val (struct pevaluator*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pev_set_value (struct pevaluator*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL  pev_assign(struct pevaluator* pev)
{
    char                p2[PEV_MAX_LEN];
    DWORD_PTR           v1;

    if (!pev_pop_val(pev, &v1) || !pev_pop(pev, p2)) return FALSE;
    if (p2[0] != '$') return PEV_ERROR1(pev, "assign: %s isn't a variable", p2);
    pev_set_value(pev, p2, v1);

    return TRUE;
}