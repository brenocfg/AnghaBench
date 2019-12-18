#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* buffer; } ;
typedef  TYPE_1__ xmlreaderinput ;
struct TYPE_11__ {int /*<<< orphan*/  utf16; int /*<<< orphan*/  encoded; int /*<<< orphan*/  code_page; TYPE_1__* input; } ;
typedef  TYPE_2__ input_buffer ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ E_OUTOFMEMORY ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  free_encoded_buffer (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ init_encoded_buffer (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* readerinput_alloc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  readerinput_free (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static HRESULT alloc_input_buffer(xmlreaderinput *input)
{
    input_buffer *buffer;
    HRESULT hr;

    input->buffer = NULL;

    buffer = readerinput_alloc(input, sizeof(*buffer));
    if (!buffer) return E_OUTOFMEMORY;

    buffer->input = input;
    buffer->code_page = ~0; /* code page is unknown at this point */
    hr = init_encoded_buffer(input, &buffer->utf16);
    if (hr != S_OK) {
        readerinput_free(input, buffer);
        return hr;
    }

    hr = init_encoded_buffer(input, &buffer->encoded);
    if (hr != S_OK) {
        free_encoded_buffer(input, &buffer->utf16);
        readerinput_free(input, buffer);
        return hr;
    }

    input->buffer = buffer;
    return S_OK;
}