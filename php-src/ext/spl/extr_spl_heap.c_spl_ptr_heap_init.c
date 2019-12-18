#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  spl_ptr_heap_dtor_func ;
typedef  int /*<<< orphan*/  spl_ptr_heap_ctor_func ;
typedef  int /*<<< orphan*/  spl_ptr_heap_cmp_func ;
struct TYPE_4__ {size_t elem_size; scalar_t__ flags; scalar_t__ count; int /*<<< orphan*/  max_size; int /*<<< orphan*/  elements; int /*<<< orphan*/  cmp; int /*<<< orphan*/  ctor; int /*<<< orphan*/  dtor; } ;
typedef  TYPE_1__ spl_ptr_heap ;

/* Variables and functions */
 int /*<<< orphan*/  PTR_HEAP_BLOCK_SIZE ; 
 int /*<<< orphan*/  ecalloc (int /*<<< orphan*/ ,size_t) ; 
 TYPE_1__* emalloc (int) ; 

__attribute__((used)) static spl_ptr_heap *spl_ptr_heap_init(spl_ptr_heap_cmp_func cmp, spl_ptr_heap_ctor_func ctor, spl_ptr_heap_dtor_func dtor, size_t elem_size) /* {{{ */
{
	spl_ptr_heap *heap = emalloc(sizeof(spl_ptr_heap));

	heap->dtor     = dtor;
	heap->ctor     = ctor;
	heap->cmp      = cmp;
	heap->elements = ecalloc(PTR_HEAP_BLOCK_SIZE, elem_size);
	heap->max_size = PTR_HEAP_BLOCK_SIZE;
	heap->count    = 0;
	heap->flags    = 0;
	heap->elem_size = elem_size;

	return heap;
}