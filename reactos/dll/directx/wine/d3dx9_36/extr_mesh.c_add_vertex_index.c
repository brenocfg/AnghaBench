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
struct word_array {scalar_t__ count; int /*<<< orphan*/ * items; } ;
struct dynamic_array {int dummy; } ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  reserve (struct dynamic_array*,scalar_t__,int) ; 

__attribute__((used)) static HRESULT add_vertex_index(struct word_array *array, WORD vertex_index)
{
    if (!reserve((struct dynamic_array *)array, array->count + 1, sizeof(array->items[0])))
        return E_OUTOFMEMORY;

    array->items[array->count++] = vertex_index;
    return S_OK;
}