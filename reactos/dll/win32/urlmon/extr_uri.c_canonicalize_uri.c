#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {char* uri; int /*<<< orphan*/  scheme_type; } ;
typedef  TYPE_1__ parse_data ;
typedef  char WCHAR ;
struct TYPE_19__ {char* canon_uri; int canon_size; int canon_len; int /*<<< orphan*/  scheme_type; } ;
typedef  TYPE_2__ Uri ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,TYPE_1__ const*,TYPE_2__*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__ const*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  canonicalize_fragment (TYPE_1__ const*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  canonicalize_hierpart (TYPE_1__ const*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  canonicalize_query (TYPE_1__ const*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  canonicalize_scheme (TYPE_1__ const*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int compute_canonicalized_length (TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (char*) ; 
 char* heap_alloc (int) ; 
 char* heap_realloc (char*,int) ; 

__attribute__((used)) static HRESULT canonicalize_uri(const parse_data *data, Uri *uri, DWORD flags) {
    INT len;

    uri->canon_uri = NULL;
    uri->canon_size = uri->canon_len = 0;

    TRACE("(%p %p %x): beginning to canonicalize URI %s.\n", data, uri, flags, debugstr_w(data->uri));

    /* First try to compute the length of the URI. */
    len = compute_canonicalized_length(data, flags);
    if(len == -1) {
        ERR("(%p %p %x): Could not compute the canonicalized length of %s.\n", data, uri, flags,
                debugstr_w(data->uri));
        return E_INVALIDARG;
    }

    uri->canon_uri = heap_alloc((len+1)*sizeof(WCHAR));
    if(!uri->canon_uri)
        return E_OUTOFMEMORY;

    uri->canon_size = len;
    if(!canonicalize_scheme(data, uri, flags, FALSE)) {
        ERR("(%p %p %x): Unable to canonicalize the scheme of the URI.\n", data, uri, flags);
        return E_INVALIDARG;
    }
    uri->scheme_type = data->scheme_type;

    if(!canonicalize_hierpart(data, uri, flags, FALSE)) {
        ERR("(%p %p %x): Unable to canonicalize the heirpart of the URI\n", data, uri, flags);
        return E_INVALIDARG;
    }

    if(!canonicalize_query(data, uri, flags, FALSE)) {
        ERR("(%p %p %x): Unable to canonicalize query string of the URI.\n",
            data, uri, flags);
        return E_INVALIDARG;
    }

    if(!canonicalize_fragment(data, uri, flags, FALSE)) {
        ERR("(%p %p %x): Unable to canonicalize fragment of the URI.\n",
            data, uri, flags);
        return E_INVALIDARG;
    }

    /* There's a possibility we didn't use all the space we allocated
     * earlier.
     */
    if(uri->canon_len < uri->canon_size) {
        /* This happens if the URI is hierarchical and dot
         * segments were removed from its path.
         */
        WCHAR *tmp = heap_realloc(uri->canon_uri, (uri->canon_len+1)*sizeof(WCHAR));
        if(!tmp)
            return E_OUTOFMEMORY;

        uri->canon_uri = tmp;
        uri->canon_size = uri->canon_len;
    }

    uri->canon_uri[uri->canon_len] = '\0';
    TRACE("(%p %p %x): finished canonicalizing the URI. uri=%s\n", data, uri, flags, debugstr_w(uri->canon_uri));

    return S_OK;
}