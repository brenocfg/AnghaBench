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
struct playlist_param {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct playlist_entry {int /*<<< orphan*/  num_params; int /*<<< orphan*/  params; } ;
typedef  int /*<<< orphan*/  bstr ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_APPEND (struct playlist_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct playlist_param) ; 
 int /*<<< orphan*/  bstrdup (struct playlist_entry*,int /*<<< orphan*/ ) ; 

void playlist_entry_add_param(struct playlist_entry *e, bstr name, bstr value)
{
    struct playlist_param p = {bstrdup(e, name), bstrdup(e, value)};
    MP_TARRAY_APPEND(e, e->params, e->num_params, p);
}