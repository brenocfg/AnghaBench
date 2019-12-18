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
struct wined3d_vertex_element {size_t input_slot; int offset; size_t output_slot; int /*<<< orphan*/  usage_idx; int /*<<< orphan*/  usage; int /*<<< orphan*/  method; scalar_t__ instance_data_step_rate; int /*<<< orphan*/  input_slot_class; int /*<<< orphan*/  format; } ;
typedef  size_t WORD ;
typedef  unsigned int UINT ;
struct TYPE_2__ {int /*<<< orphan*/  usage_idx; int /*<<< orphan*/  usage; } ;
typedef  size_t DWORD ;
typedef  int D3DVSD_TOKENTYPE ;

/* Variables and functions */
 size_t const D3DVSD_DATALOADTYPEMASK ; 
 size_t const D3DVSD_DATATYPEMASK ; 
 size_t const D3DVSD_DATATYPESHIFT ; 
 size_t const D3DVSD_END () ; 
 int D3DVSD_SKIPCOUNTMASK ; 
 int D3DVSD_SKIPCOUNTSHIFT ; 
 size_t const D3DVSD_STREAMNUMBERMASK ; 
 size_t const D3DVSD_STREAMNUMBERSHIFT ; 
 size_t const D3DVSD_STREAMTESSMASK ; 
 size_t const D3DVSD_TOKENTYPEMASK ; 
 size_t const D3DVSD_TOKENTYPESHIFT ; 
 int D3DVSD_TOKEN_STREAM ; 
 int D3DVSD_TOKEN_STREAMDATA ; 
 size_t const D3DVSD_VERTEXREGMASK ; 
 size_t const D3DVSD_VERTEXREGSHIFT ; 
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  WINED3D_DECL_METHOD_DEFAULT ; 
 int /*<<< orphan*/  WINED3D_INPUT_PER_VERTEX_DATA ; 
 struct wined3d_vertex_element* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  parse_token (size_t const*) ; 
 int /*<<< orphan*/ * wined3d_format_lookup ; 
 scalar_t__* wined3d_type_sizes ; 
 TYPE_1__* wined3d_usage_lookup ; 

__attribute__((used)) static UINT convert_to_wined3d_declaration(const DWORD *d3d8_elements, DWORD *d3d8_elements_size,
        struct wined3d_vertex_element **wined3d_elements)
{
    struct wined3d_vertex_element *element;
    const DWORD *token = d3d8_elements;
    D3DVSD_TOKENTYPE token_type;
    unsigned int element_count = 0;
    WORD stream = 0;
    int offset = 0;

    TRACE("d3d8_elements %p, d3d8_elements_size %p, wined3d_elements %p\n", d3d8_elements, d3d8_elements_size, wined3d_elements);

    /* 128 should be enough for anyone... */
    *wined3d_elements = heap_alloc_zero(128 * sizeof(**wined3d_elements));
    while (D3DVSD_END() != *token)
    {
        token_type = ((*token & D3DVSD_TOKENTYPEMASK) >> D3DVSD_TOKENTYPESHIFT);

        if (token_type == D3DVSD_TOKEN_STREAM && !(*token & D3DVSD_STREAMTESSMASK))
        {
            stream = ((*token & D3DVSD_STREAMNUMBERMASK) >> D3DVSD_STREAMNUMBERSHIFT);
            offset = 0;
        } else if (token_type == D3DVSD_TOKEN_STREAMDATA && !(*token & D3DVSD_DATALOADTYPEMASK)) {
            DWORD type = ((*token & D3DVSD_DATATYPEMASK) >> D3DVSD_DATATYPESHIFT);
            DWORD reg  = ((*token & D3DVSD_VERTEXREGMASK) >> D3DVSD_VERTEXREGSHIFT);

            TRACE("Adding element %d:\n", element_count);

            element = *wined3d_elements + element_count++;
            element->format = wined3d_format_lookup[type];
            element->input_slot = stream;
            element->offset = offset;
            element->output_slot = reg;
            element->input_slot_class = WINED3D_INPUT_PER_VERTEX_DATA;
            element->instance_data_step_rate = 0;
            element->method = WINED3D_DECL_METHOD_DEFAULT;
            element->usage = wined3d_usage_lookup[reg].usage;
            element->usage_idx = wined3d_usage_lookup[reg].usage_idx;

            offset += wined3d_type_sizes[type];
        } else if (token_type == D3DVSD_TOKEN_STREAMDATA && (*token & D3DVSD_DATALOADTYPEMASK)) {
            TRACE(" 0x%08x SKIP(%u)\n", token_type, ((token_type & D3DVSD_SKIPCOUNTMASK) >> D3DVSD_SKIPCOUNTSHIFT));
            offset += sizeof(DWORD) * ((token_type & D3DVSD_SKIPCOUNTMASK) >> D3DVSD_SKIPCOUNTSHIFT);
        }

        if (element_count >= 127) {
            ERR("More than 127 elements?\n");
            break;
        }

        token += parse_token(token);
    }

    *d3d8_elements_size = (++token - d3d8_elements) * sizeof(DWORD);

    return element_count;
}