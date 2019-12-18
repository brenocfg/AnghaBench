#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wined3d_vec4 {int /*<<< orphan*/  x; } ;
struct wined3d_gl_info {int dummy; } ;
struct constant_heap {unsigned int size; TYPE_1__* entries; } ;
struct TYPE_2__ {scalar_t__ version; unsigned int idx; } ;
typedef  int GLint ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
#define  HEAP_NODE_POP 130 
#define  HEAP_NODE_TRAVERSE_LEFT 129 
#define  HEAP_NODE_TRAVERSE_RIGHT 128 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  glUniform4fv (int const,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void walk_constant_heap(const struct wined3d_gl_info *gl_info, const struct wined3d_vec4 *constants,
        const GLint *constant_locations, const struct constant_heap *heap, unsigned char *stack, DWORD version)
{
    unsigned int start = ~0U, end = 0;
    int stack_idx = 0;
    unsigned int heap_idx = 1;
    unsigned int idx;

    if (heap->entries[heap_idx].version <= version) return;

    idx = heap->entries[heap_idx].idx;
    if (constant_locations[idx] != -1)
        start = end = idx;
    stack[stack_idx] = HEAP_NODE_TRAVERSE_LEFT;

    while (stack_idx >= 0)
    {
        /* Note that we fall through to the next case statement. */
        switch(stack[stack_idx])
        {
            case HEAP_NODE_TRAVERSE_LEFT:
            {
                unsigned int left_idx = heap_idx << 1;
                if (left_idx < heap->size && heap->entries[left_idx].version > version)
                {
                    heap_idx = left_idx;
                    idx = heap->entries[heap_idx].idx;
                    if (constant_locations[idx] != -1)
                    {
                        if (start > idx)
                            start = idx;
                        if (end < idx)
                            end = idx;
                    }

                    stack[stack_idx++] = HEAP_NODE_TRAVERSE_RIGHT;
                    stack[stack_idx] = HEAP_NODE_TRAVERSE_LEFT;
                    break;
                }
            }

            case HEAP_NODE_TRAVERSE_RIGHT:
            {
                unsigned int right_idx = (heap_idx << 1) + 1;
                if (right_idx < heap->size && heap->entries[right_idx].version > version)
                {
                    heap_idx = right_idx;
                    idx = heap->entries[heap_idx].idx;
                    if (constant_locations[idx] != -1)
                    {
                        if (start > idx)
                            start = idx;
                        if (end < idx)
                            end = idx;
                    }

                    stack[stack_idx++] = HEAP_NODE_POP;
                    stack[stack_idx] = HEAP_NODE_TRAVERSE_LEFT;
                    break;
                }
            }

            case HEAP_NODE_POP:
                heap_idx >>= 1;
                --stack_idx;
                break;
        }
    }
    if (start <= end)
        GL_EXTCALL(glUniform4fv(constant_locations[start], end - start + 1, &constants[start].x));
    checkGLcall("walk_constant_heap()");
}