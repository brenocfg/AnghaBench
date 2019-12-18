#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int allocated; scalar_t__ written; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ encoded_buffer ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  heap_alloc (int const) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static HRESULT init_encoded_buffer(encoded_buffer *buffer)
{
    const int initial_len = 0x1000;
    buffer->data = heap_alloc(initial_len);
    if (!buffer->data) return E_OUTOFMEMORY;

    memset(buffer->data, 0, 4);
    buffer->allocated = initial_len;
    buffer->written = 0;

    return S_OK;
}