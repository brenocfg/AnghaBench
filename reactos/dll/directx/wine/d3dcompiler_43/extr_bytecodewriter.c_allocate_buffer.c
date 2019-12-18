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
struct bytecode_buffer {int alloc_size; int /*<<< orphan*/  state; void* data; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int BYTECODEBUFFER_INITIAL_SIZE ; 
 int /*<<< orphan*/  S_OK ; 
 void* d3dcompiler_alloc (int) ; 
 int /*<<< orphan*/  d3dcompiler_free (struct bytecode_buffer*) ; 

__attribute__((used)) static struct bytecode_buffer *allocate_buffer(void) {
    struct bytecode_buffer *ret;

    ret = d3dcompiler_alloc(sizeof(*ret));
    if(!ret) return NULL;

    ret->alloc_size = BYTECODEBUFFER_INITIAL_SIZE;
    ret->data = d3dcompiler_alloc(sizeof(DWORD) * ret->alloc_size);
    if(!ret->data) {
        d3dcompiler_free(ret);
        return NULL;
    }
    ret->state = S_OK;
    return ret;
}