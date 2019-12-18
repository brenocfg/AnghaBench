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
typedef  int /*<<< orphan*/  xmlreader ;
typedef  int /*<<< orphan*/  strval ;
typedef  char WCHAR ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WC_E_LESSTHAN ; 
 int /*<<< orphan*/  WC_E_QUOTE ; 
 scalar_t__ is_wchar_space (char) ; 
 scalar_t__ reader_get_cur (int /*<<< orphan*/ *) ; 
 char* reader_get_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_init_strvalue (scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_parse_reference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reader_skipn (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static HRESULT reader_parse_attvalue(xmlreader *reader, strval *value)
{
    WCHAR *ptr, quote;
    UINT start;

    ptr = reader_get_ptr(reader);

    /* skip opening quote */
    quote = *ptr;
    if (quote != '\"' && quote != '\'') return WC_E_QUOTE;
    reader_skipn(reader, 1);

    ptr = reader_get_ptr(reader);
    start = reader_get_cur(reader);
    while (*ptr)
    {
        if (*ptr == '<') return WC_E_LESSTHAN;

        if (*ptr == quote)
        {
            reader_init_strvalue(start, reader_get_cur(reader)-start, value);
            /* skip closing quote */
            reader_skipn(reader, 1);
            return S_OK;
        }

        if (*ptr == '&')
        {
            HRESULT hr = reader_parse_reference(reader);
            if (FAILED(hr)) return hr;
        }
        else
        {
            /* replace all whitespace chars with ' ' */
            if (is_wchar_space(*ptr)) *ptr = ' ';
            reader_skipn(reader, 1);
        }
        ptr = reader_get_ptr(reader);
    }

    return WC_E_QUOTE;
}