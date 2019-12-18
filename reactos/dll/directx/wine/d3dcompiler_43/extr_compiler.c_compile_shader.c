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
struct target_info {int type; char sm_major; char sm_minor; int /*<<< orphan*/  support; } ;
struct bwriter_shader {int dummy; } ;
typedef  enum shader_type { ____Placeholder_shader_type } shader_type ;
typedef  int /*<<< orphan*/  ID3DBlob ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  char DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  D3DCreateBlob (char,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  D3DERR_INVALIDCALL ; 
 int /*<<< orphan*/  D3DXERR_INVALIDDATA ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 char* ID3D10Blob_GetBufferPointer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3D10Blob_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SlDeleteShader (struct bwriter_shader*) ; 
 int /*<<< orphan*/  SlWriteBytecode (struct bwriter_shader*,int,char**,char*) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  debugstr_a (char const*) ; 
 struct target_info* get_target_info (char const*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,char) ; 
 struct bwriter_shader* parse_hlsl_shader (char const*,int,char,char,char const*,char**) ; 
 char strlen (char const*) ; 

__attribute__((used)) static HRESULT compile_shader(const char *preproc_shader, const char *target, const char *entrypoint,
        ID3DBlob **shader_blob, ID3DBlob **error_messages)
{
    struct bwriter_shader *shader;
    char *messages = NULL;
    HRESULT hr;
    DWORD *res, size, major, minor;
    ID3DBlob *buffer;
    char *pos;
    enum shader_type shader_type;
    const struct target_info *info;

    TRACE("Preprocessed shader source: %s\n", debugstr_a(preproc_shader));

    TRACE("Checking compilation target %s\n", debugstr_a(target));
    info = get_target_info(target);
    if (!info)
    {
        FIXME("Unknown compilation target %s\n", debugstr_a(target));
        return D3DERR_INVALIDCALL;
    }
    else
    {
        if (!info->support)
        {
            FIXME("Compilation target %s not yet supported\n", debugstr_a(target));
            return D3DERR_INVALIDCALL;
        }
        else
        {
            shader_type = info->type;
            major = info->sm_major;
            minor = info->sm_minor;
        }
    }

    shader = parse_hlsl_shader(preproc_shader, shader_type, major, minor, entrypoint, &messages);

    if (messages)
    {
        TRACE("Compiler messages:\n");
        TRACE("%s\n", debugstr_a(messages));

        TRACE("Shader source:\n");
        TRACE("%s\n", debugstr_a(preproc_shader));

        if (error_messages)
        {
            const char *preproc_messages = *error_messages ? ID3D10Blob_GetBufferPointer(*error_messages) : NULL;

            size = strlen(messages) + (preproc_messages ? strlen(preproc_messages) : 0) + 1;
            hr = D3DCreateBlob(size, &buffer);
            if (FAILED(hr))
            {
                HeapFree(GetProcessHeap(), 0, messages);
                if (shader) SlDeleteShader(shader);
                return hr;
            }
            pos = ID3D10Blob_GetBufferPointer(buffer);
            if (preproc_messages)
            {
                memcpy(pos, preproc_messages, strlen(preproc_messages) + 1);
                pos += strlen(preproc_messages);
            }
            memcpy(pos, messages, strlen(messages) + 1);

            if (*error_messages) ID3D10Blob_Release(*error_messages);
            *error_messages = buffer;
        }
        HeapFree(GetProcessHeap(), 0, messages);
    }

    if (!shader)
    {
        ERR("HLSL shader parsing failed.\n");
        return D3DXERR_INVALIDDATA;
    }

    hr = SlWriteBytecode(shader, 9, &res, &size);
    SlDeleteShader(shader);
    if (FAILED(hr))
    {
        ERR("SlWriteBytecode failed with error 0x%08x.\n", hr);
        return D3DXERR_INVALIDDATA;
    }

    if (shader_blob)
    {
        hr = D3DCreateBlob(size, &buffer);
        if (FAILED(hr))
        {
            HeapFree(GetProcessHeap(), 0, res);
            return hr;
        }
        memcpy(ID3D10Blob_GetBufferPointer(buffer), res, size);
        *shader_blob = buffer;
    }

    HeapFree(GetProcessHeap(), 0, res);

    return S_OK;
}