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
struct file_backed_buffer {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct file_backed_buffer*) ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
free_post_buffer(void *data)
{
    struct file_backed_buffer *buf = data;

    munmap(buf->ptr, buf->size);
    free(buf);
}