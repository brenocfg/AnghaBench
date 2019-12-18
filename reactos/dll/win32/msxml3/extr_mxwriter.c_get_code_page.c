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
typedef  size_t xml_encoding ;
struct xml_encoding_data {int /*<<< orphan*/  cp; } ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOTIMPL ; 
 int /*<<< orphan*/  FIXME (char*,size_t) ; 
 int /*<<< orphan*/  S_OK ; 
 size_t XmlEncoding_Unknown ; 
 struct xml_encoding_data* xml_encoding_map ; 

__attribute__((used)) static HRESULT get_code_page(xml_encoding encoding, UINT *cp)
{
    const struct xml_encoding_data *data;

    if (encoding == XmlEncoding_Unknown)
    {
        FIXME("unsupported encoding %d\n", encoding);
        return E_NOTIMPL;
    }

    data = &xml_encoding_map[encoding];
    *cp = data->cp;

    return S_OK;
}