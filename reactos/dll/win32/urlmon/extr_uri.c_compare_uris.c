#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ scheme_type; int authority_start; int scheme_start; scalar_t__ scheme_len; char* canon_uri; int userinfo_start; scalar_t__ userinfo_len; int host_start; scalar_t__ host_len; scalar_t__ port; int path_start; scalar_t__ path_len; int query_start; scalar_t__ query_len; int fragment_start; scalar_t__ fragment_len; scalar_t__ has_port; } ;
typedef  TYPE_1__ Uri ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ StrCmpNIW (char*,char*,scalar_t__) ; 
 scalar_t__ StrCmpNW (char*,char*,scalar_t__) ; 
 int TRUE ; 
 scalar_t__ URL_SCHEME_FILE ; 
 scalar_t__ URL_SCHEME_UNKNOWN ; 
 int /*<<< orphan*/  compare_file_paths (TYPE_1__ const*,TYPE_1__ const*,int*) ; 

__attribute__((used)) static HRESULT compare_uris(const Uri *a, const Uri *b, BOOL *ret) {
    const BOOL known_scheme = a->scheme_type != URL_SCHEME_UNKNOWN;
    const BOOL are_hierarchical = a->authority_start > -1 && b->authority_start > -1;
    HRESULT hres;

    *ret = FALSE;

    if(a->scheme_type != b->scheme_type)
        return S_OK;

    /* Only compare the scheme names (if any) if their unknown scheme types. */
    if(!known_scheme) {
        if((a->scheme_start > -1 && b->scheme_start > -1) &&
           (a->scheme_len == b->scheme_len)) {
            /* Make sure the schemes are the same. */
            if(StrCmpNW(a->canon_uri+a->scheme_start, b->canon_uri+b->scheme_start, a->scheme_len))
                return S_OK;
        } else if(a->scheme_len != b->scheme_len)
            /* One of the Uri's has a scheme name, while the other doesn't. */
            return S_OK;
    }

    /* If they have a userinfo component, perform case sensitive compare. */
    if((a->userinfo_start > -1 && b->userinfo_start > -1) &&
       (a->userinfo_len == b->userinfo_len)) {
        if(StrCmpNW(a->canon_uri+a->userinfo_start, b->canon_uri+b->userinfo_start, a->userinfo_len))
            return S_OK;
    } else if(a->userinfo_len != b->userinfo_len)
        /* One of the Uri's had a userinfo, while the other one doesn't. */
        return S_OK;

    /* Check if they have a host name. */
    if((a->host_start > -1 && b->host_start > -1) &&
       (a->host_len == b->host_len)) {
        /* Perform a case insensitive compare if they are a known scheme type. */
        if(known_scheme) {
            if(StrCmpNIW(a->canon_uri+a->host_start, b->canon_uri+b->host_start, a->host_len))
                return S_OK;
        } else if(StrCmpNW(a->canon_uri+a->host_start, b->canon_uri+b->host_start, a->host_len))
            return S_OK;
    } else if(a->host_len != b->host_len)
        /* One of the Uri's had a host, while the other one didn't. */
        return S_OK;

    if(a->has_port && b->has_port) {
        if(a->port != b->port)
            return S_OK;
    } else if(a->has_port || b->has_port)
        /* One had a port, while the other one didn't. */
        return S_OK;

    /* Windows is weird with how it handles paths. For example
     * One URI could be "http://google.com" (after canonicalization)
     * and one could be "http://google.com/" and the IsEqual function
     * would still evaluate to TRUE, but, only if they are both hierarchical
     * URIs.
     */
    if(a->scheme_type == URL_SCHEME_FILE) {
        BOOL cmp;

        hres = compare_file_paths(a, b, &cmp);
        if(FAILED(hres) || !cmp)
            return hres;
    } else if((a->path_start > -1 && b->path_start > -1) &&
       (a->path_len == b->path_len)) {
        if(StrCmpNW(a->canon_uri+a->path_start, b->canon_uri+b->path_start, a->path_len))
            return S_OK;
    } else if(are_hierarchical && a->path_len == -1 && b->path_len == 0) {
        if(*(a->canon_uri+a->path_start) != '/')
            return S_OK;
    } else if(are_hierarchical && b->path_len == 1 && a->path_len == 0) {
        if(*(b->canon_uri+b->path_start) != '/')
            return S_OK;
    } else if(a->path_len != b->path_len)
        return S_OK;

    /* Compare the query strings of the two URIs. */
    if((a->query_start > -1 && b->query_start > -1) &&
       (a->query_len == b->query_len)) {
        if(StrCmpNW(a->canon_uri+a->query_start, b->canon_uri+b->query_start, a->query_len))
            return S_OK;
    } else if(a->query_len != b->query_len)
        return S_OK;

    if((a->fragment_start > -1 && b->fragment_start > -1) &&
       (a->fragment_len == b->fragment_len)) {
        if(StrCmpNW(a->canon_uri+a->fragment_start, b->canon_uri+b->fragment_start, a->fragment_len))
            return S_OK;
    } else if(a->fragment_len != b->fragment_len)
        return S_OK;

    /* If we get here, the two URIs are equivalent. */
    *ret = TRUE;
    return S_OK;
}