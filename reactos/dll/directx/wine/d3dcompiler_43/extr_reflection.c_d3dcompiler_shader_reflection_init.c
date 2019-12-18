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
struct dxbc_section {int tag; int /*<<< orphan*/  data_size; int /*<<< orphan*/  data; } ;
struct dxbc {unsigned int count; struct dxbc_section* sections; } ;
struct TYPE_2__ {int /*<<< orphan*/ * lpVtbl; } ;
struct d3dcompiler_shader_reflection {int refcount; int /*<<< orphan*/  target; void* pcsg; void* osgn; void* isgn; int /*<<< orphan*/  types; TYPE_1__ ID3D11ShaderReflection_iface; } ;
typedef  int /*<<< orphan*/  SIZE_T ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 void* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
#define  TAG_ISGN 135 
#define  TAG_OSG5 134 
#define  TAG_OSGN 133 
#define  TAG_PCSG 132 
#define  TAG_RDEF 131 
#define  TAG_SHDR 130 
#define  TAG_SHEX 129 
#define  TAG_STAT 128 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  d3dcompiler_parse_rdef (struct d3dcompiler_shader_reflection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3dcompiler_parse_shdr (struct d3dcompiler_shader_reflection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3dcompiler_parse_signature (void*,struct dxbc_section*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3dcompiler_parse_stat (struct d3dcompiler_shader_reflection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d3dcompiler_shader_reflection_type_compare ; 
 int /*<<< orphan*/  d3dcompiler_shader_reflection_vtbl ; 
 int /*<<< orphan*/  debugstr_an (char const*,int) ; 
 int /*<<< orphan*/  dxbc_destroy (struct dxbc*) ; 
 int /*<<< orphan*/  dxbc_parse (void const*,int /*<<< orphan*/ ,struct dxbc*) ; 
 int /*<<< orphan*/  reflection_cleanup (struct d3dcompiler_shader_reflection*) ; 
 int /*<<< orphan*/  wine_rb_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT d3dcompiler_shader_reflection_init(struct d3dcompiler_shader_reflection *reflection,
        const void *data, SIZE_T data_size)
{
    struct dxbc src_dxbc;
    HRESULT hr;
    unsigned int i;

    reflection->ID3D11ShaderReflection_iface.lpVtbl = &d3dcompiler_shader_reflection_vtbl;
    reflection->refcount = 1;

    wine_rb_init(&reflection->types, d3dcompiler_shader_reflection_type_compare);

    hr = dxbc_parse(data, data_size, &src_dxbc);
    if (FAILED(hr))
    {
        WARN("Failed to parse reflection\n");
        return hr;
    }

    for (i = 0; i < src_dxbc.count; ++i)
    {
        struct dxbc_section *section = &src_dxbc.sections[i];

        switch (section->tag)
        {
            case TAG_RDEF:
                hr = d3dcompiler_parse_rdef(reflection, section->data, section->data_size);
                if (FAILED(hr))
                {
                    WARN("Failed to parse RDEF section.\n");
                    goto err_out;
                }
                break;

            case TAG_ISGN:
                reflection->isgn = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*reflection->isgn));
                if (!reflection->isgn)
                {
                    ERR("Failed to allocate ISGN memory.\n");
                    hr = E_OUTOFMEMORY;
                    goto err_out;
                }

                hr = d3dcompiler_parse_signature(reflection->isgn, section, reflection->target);
                if (FAILED(hr))
                {
                    WARN("Failed to parse section ISGN.\n");
                    goto err_out;
                }
                break;

            case TAG_OSG5:
            case TAG_OSGN:
                reflection->osgn = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*reflection->osgn));
                if (!reflection->osgn)
                {
                    ERR("Failed to allocate OSGN memory.\n");
                    hr = E_OUTOFMEMORY;
                    goto err_out;
                }

                hr = d3dcompiler_parse_signature(reflection->osgn, section, reflection->target);
                if (FAILED(hr))
                {
                    WARN("Failed to parse section OSGN.\n");
                    goto err_out;
                }
                break;

            case TAG_PCSG:
                reflection->pcsg = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*reflection->pcsg));
                if (!reflection->pcsg)
                {
                    ERR("Failed to allocate PCSG memory.\n");
                    hr = E_OUTOFMEMORY;
                    goto err_out;
                }

                hr = d3dcompiler_parse_signature(reflection->pcsg, section, reflection->target);
                if (FAILED(hr))
                {
                    WARN("Failed to parse section PCSG.\n");
                    goto err_out;
                }
                break;

            case TAG_SHEX:
            case TAG_SHDR:
                hr = d3dcompiler_parse_shdr(reflection, section->data, section->data_size);
                if (FAILED(hr))
                {
                    WARN("Failed to parse SHDR section.\n");
                    goto err_out;
                }
                break;

            case TAG_STAT:
                hr = d3dcompiler_parse_stat(reflection, section->data, section->data_size);
                if (FAILED(hr))
                {
                    WARN("Failed to parse section STAT.\n");
                    goto err_out;
                }
                break;

            default:
                FIXME("Unhandled section %s!\n", debugstr_an((const char *)&section->tag, 4));
                break;
        }
    }

    dxbc_destroy(&src_dxbc);

    return hr;

err_out:
    reflection_cleanup(reflection);
    dxbc_destroy(&src_dxbc);

    return hr;
}