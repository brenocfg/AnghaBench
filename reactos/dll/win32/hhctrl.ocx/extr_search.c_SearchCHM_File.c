#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_9__ {int len; char* buf; } ;
typedef  TYPE_1__ strbuf_t ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int BLOCK_SIZE ; 
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IStorage_OpenStream (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int) ; 
 int /*<<< orphan*/  STGM_READ ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _strnicmp (char*,char*,int) ; 
 int /*<<< orphan*/  debugstr_w (char const*) ; 
 int /*<<< orphan*/  get_node_name (TYPE_1__*,TYPE_1__*) ; 
 char* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (char*) ; 
 char* heap_realloc (char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 scalar_t__ next_content (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ next_node (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  strbuf_free (TYPE_1__*) ; 
 int /*<<< orphan*/  strbuf_init (TYPE_1__*) ; 
 int /*<<< orphan*/  strbuf_zero (TYPE_1__*) ; 
 int /*<<< orphan*/  stream_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strstr (char*,char const*) ; 
 char tolower (char) ; 

__attribute__((used)) static WCHAR *SearchCHM_File(IStorage *pStorage, const WCHAR *file, const char *needle)
{
    char *buffer = heap_alloc(BLOCK_SIZE);
    strbuf_t content, node, node_name;
    IStream *temp_stream = NULL;
    DWORD i, buffer_size = 0;
    WCHAR *title = NULL;
    BOOL found = FALSE;
    stream_t stream;
    HRESULT hres;

    hres = IStorage_OpenStream(pStorage, file, NULL, STGM_READ, 0, &temp_stream);
    if(FAILED(hres)) {
        FIXME("Could not open '%s' stream: %08x\n", debugstr_w(file), hres);
        goto cleanup;
    }

    strbuf_init(&node);
    strbuf_init(&content);
    strbuf_init(&node_name);

    stream_init(&stream, temp_stream);

    /* Remove all HTML formatting and record the title */
    while(next_node(&stream, &node)) {
        get_node_name(&node, &node_name);

        if(next_content(&stream, &content) && content.len > 1)
        {
            char *text = &content.buf[1];
            int textlen = content.len-1;

            if(!_strnicmp(node_name.buf, "title", -1))
            {
                int wlen = MultiByteToWideChar(CP_ACP, 0, text, textlen, NULL, 0);
                title = heap_alloc((wlen+1)*sizeof(WCHAR));
                MultiByteToWideChar(CP_ACP, 0, text, textlen, title, wlen);
                title[wlen] = 0;
            }

            buffer = heap_realloc(buffer, buffer_size + textlen + 1);
            memcpy(&buffer[buffer_size], text, textlen);
            buffer[buffer_size + textlen] = '\0';
            buffer_size += textlen;
        }

        strbuf_zero(&node);
        strbuf_zero(&content);
    }

    /* Convert the buffer to lower case for comparison against the
     * requested text (already in lower case).
     */
    for(i=0;i<buffer_size;i++)
        buffer[i] = tolower(buffer[i]);

    /* Search the decoded buffer for the requested text */
    if(strstr(buffer, needle))
        found = TRUE;

    strbuf_free(&node);
    strbuf_free(&content);
    strbuf_free(&node_name);

cleanup:
    heap_free(buffer);
    if(temp_stream)
        IStream_Release(temp_stream);
    if(!found)
    {
        heap_free(title);
        return NULL;
    }
    return title;
}