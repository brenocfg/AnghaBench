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
struct bwriter_shader {int dummy; } ;
typedef  int /*<<< orphan*/  ID3DBlob ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  char DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CopyMemory (char*,char const*,char) ; 
 int /*<<< orphan*/  D3DCreateBlob (char,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  D3DXERR_INVALIDDATA ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 char* ID3D10Blob_GetBufferPointer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ID3D10Blob_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 struct bwriter_shader* SlAssembleShader (char const*,char**) ; 
 int /*<<< orphan*/  SlDeleteShader (struct bwriter_shader*) ; 
 int /*<<< orphan*/  SlWriteBytecode (struct bwriter_shader*,int,char**,char*) ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  debugstr_a (char const*) ; 
 char strlen (char const*) ; 

__attribute__((used)) static HRESULT assemble_shader(const char *preproc_shader,
        ID3DBlob **shader_blob, ID3DBlob **error_messages)
{
    struct bwriter_shader *shader;
    char *messages = NULL;
    HRESULT hr;
    DWORD *res, size;
    ID3DBlob *buffer;
    char *pos;

    shader = SlAssembleShader(preproc_shader, &messages);

    if (messages)
    {
        TRACE("Assembler messages:\n");
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
                CopyMemory(pos, preproc_messages, strlen(preproc_messages) + 1);
                pos += strlen(preproc_messages);
            }
            CopyMemory(pos, messages, strlen(messages) + 1);

            if (*error_messages) ID3D10Blob_Release(*error_messages);
            *error_messages = buffer;
        }
        HeapFree(GetProcessHeap(), 0, messages);
    }

    if (shader == NULL)
    {
        ERR("Asm reading failed\n");
        return D3DXERR_INVALIDDATA;
    }

    hr = SlWriteBytecode(shader, 9, &res, &size);
    SlDeleteShader(shader);
    if (FAILED(hr))
    {
        ERR("SlWriteBytecode failed with 0x%08x\n", hr);
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
        CopyMemory(ID3D10Blob_GetBufferPointer(buffer), res, size);
        *shader_blob = buffer;
    }

    HeapFree(GetProcessHeap(), 0, res);

    return S_OK;
}