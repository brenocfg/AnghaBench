#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  uri; } ;
typedef  TYPE_1__ parse_data ;
struct TYPE_16__ {int canon_len; } ;
typedef  TYPE_2__ Uri ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__ const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  canonicalize_fragment (TYPE_1__ const*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  canonicalize_hierpart (TYPE_1__ const*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  canonicalize_query (TYPE_1__ const*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  canonicalize_scheme (TYPE_1__ const*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int compute_canonicalized_length(const parse_data *data, DWORD flags) {
    Uri uri;

    memset(&uri, 0, sizeof(Uri));

    TRACE("(%p %x): Beginning to compute canonicalized length for URI %s\n", data, flags,
            debugstr_w(data->uri));

    if(!canonicalize_scheme(data, &uri, flags, TRUE)) {
        ERR("(%p %x): Failed to compute URI scheme length.\n", data, flags);
        return -1;
    }

    if(!canonicalize_hierpart(data, &uri, flags, TRUE)) {
        ERR("(%p %x): Failed to compute URI hierpart length.\n", data, flags);
        return -1;
    }

    if(!canonicalize_query(data, &uri, flags, TRUE)) {
        ERR("(%p %x): Failed to compute query string length.\n", data, flags);
        return -1;
    }

    if(!canonicalize_fragment(data, &uri, flags, TRUE)) {
        ERR("(%p %x): Failed to compute fragment length.\n", data, flags);
        return -1;
    }

    TRACE("(%p %x): Finished computing canonicalized URI length. length=%d\n", data, flags, uri.canon_len);

    return uri.canon_len;
}