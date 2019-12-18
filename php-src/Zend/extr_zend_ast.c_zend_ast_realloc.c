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

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 
 void* zend_ast_alloc (size_t) ; 

__attribute__((used)) static inline void *zend_ast_realloc(void *old, size_t old_size, size_t new_size) {
	void *new = zend_ast_alloc(new_size);
	memcpy(new, old, old_size);
	return new;
}