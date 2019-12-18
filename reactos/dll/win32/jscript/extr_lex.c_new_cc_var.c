#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccval_t ;
struct TYPE_5__ {int name_len; struct TYPE_5__* next; int /*<<< orphan*/  name; int /*<<< orphan*/  val; } ;
typedef  TYPE_1__ cc_var_t ;
struct TYPE_6__ {TYPE_1__* vars; } ;
typedef  TYPE_2__ cc_ctx_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* heap_alloc (int) ; 
 int lstrlenW (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static BOOL new_cc_var(cc_ctx_t *cc, const WCHAR *name, int len, ccval_t v)
{
    cc_var_t *new_v;

    if(len == -1)
        len = lstrlenW(name);

    new_v = heap_alloc(sizeof(cc_var_t) + (len+1)*sizeof(WCHAR));
    if(!new_v)
        return FALSE;

    new_v->val = v;
    memcpy(new_v->name, name, (len+1)*sizeof(WCHAR));
    new_v->name_len = len;
    new_v->next = cc->vars;
    cc->vars = new_v;
    return TRUE;
}