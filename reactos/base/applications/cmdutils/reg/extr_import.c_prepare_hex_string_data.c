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
struct parser {scalar_t__ data_type; int data_size; scalar_t__* data; scalar_t__ is_unicode; } ;
typedef  scalar_t__ WCHAR ;
typedef  int DWORD ;
typedef  scalar_t__ BYTE ;

/* Variables and functions */
 scalar_t__* GetWideStringN (scalar_t__*,size_t,size_t*) ; 
 scalar_t__ REG_EXPAND_SZ ; 
 scalar_t__ REG_MULTI_SZ ; 
 scalar_t__ REG_SZ ; 
 int /*<<< orphan*/  heap_free (scalar_t__*) ; 

__attribute__((used)) static void prepare_hex_string_data(struct parser *parser)
{
    if (parser->data_type == REG_EXPAND_SZ || parser->data_type == REG_MULTI_SZ ||
        parser->data_type == REG_SZ)
    {
        if (parser->is_unicode)
        {
            WCHAR *data = parser->data;
            DWORD len = parser->data_size / sizeof(WCHAR);

            if (data[len - 1] != 0)
            {
                data[len] = 0;
                parser->data_size += sizeof(WCHAR);
            }
        }
        else
        {
            BYTE *data = parser->data;

            if (data[parser->data_size - 1] != 0)
            {
                data[parser->data_size] = 0;
                parser->data_size++;
            }

            parser->data = GetWideStringN(parser->data, parser->data_size, &parser->data_size);
            parser->data_size *= sizeof(WCHAR);
            heap_free(data);
        }
    }
}