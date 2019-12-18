#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  stream_t ;
struct TYPE_11__ {int len; int /*<<< orphan*/ * buf; } ;
typedef  TYPE_1__ strbuf_t ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_12__ {int /*<<< orphan*/ * pStorage; } ;
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int /*<<< orphan*/  IStream ;
typedef  int /*<<< orphan*/  IStorage ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ CHMInfo ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStorage_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStorage_OpenStream (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IStorage_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IStream_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STGM_READ ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 int /*<<< orphan*/  _strnicmp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * debugstr_w (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_node_name (TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ next_content (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ next_node (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  strbuf_free (TYPE_1__*) ; 
 int /*<<< orphan*/  strbuf_init (TYPE_1__*) ; 
 int /*<<< orphan*/  strbuf_zero (TYPE_1__*) ; 
 int /*<<< orphan*/ * strdupnAtoW (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stream_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

WCHAR *GetDocumentTitle(CHMInfo *info, LPCWSTR document)
{
    strbuf_t node, node_name, content;
    WCHAR *document_title = NULL;
    IStream *str = NULL;
    IStorage *storage;
    stream_t stream;
    HRESULT hres;

    TRACE("%s\n", debugstr_w(document));

    storage = info->pStorage;
    if(!storage) {
        WARN("Could not open storage to obtain the title for a document.\n");
        return NULL;
    }
    IStorage_AddRef(storage);

    hres = IStorage_OpenStream(storage, document, NULL, STGM_READ, 0, &str);
    IStorage_Release(storage);
    if(FAILED(hres))
        WARN("Could not open stream: %08x\n", hres);

    stream_init(&stream, str);
    strbuf_init(&node);
    strbuf_init(&content);
    strbuf_init(&node_name);

    while(next_node(&stream, &node)) {
        get_node_name(&node, &node_name);

        TRACE("%s\n", node.buf);

        if(!_strnicmp(node_name.buf, "title", -1)) {
            if(next_content(&stream, &content) && content.len > 1)
            {
                document_title = strdupnAtoW(&content.buf[1], content.len-1);
                FIXME("magic: %s\n", debugstr_w(document_title));
                break;
            }
        }

        strbuf_zero(&node);
    }

    strbuf_free(&node);
    strbuf_free(&content);
    strbuf_free(&node_name);
    IStream_Release(str);

    return document_title;
}