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
typedef  int /*<<< orphan*/  data_stream_t ;
typedef  int /*<<< orphan*/  chunked_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void chunked_destroy(data_stream_t *stream)
{
    chunked_stream_t *chunked_stream = (chunked_stream_t*)stream;
    heap_free(chunked_stream);
}