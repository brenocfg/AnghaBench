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
struct query {int /*<<< orphan*/  view; int /*<<< orphan*/  mem; } ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  IEnumWbemClassObject ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ E_OUTOFMEMORY ; 
 scalar_t__ EnumWbemClassObject_create (struct query*,void**) ; 
 scalar_t__ S_OK ; 
 struct query* create_query () ; 
 scalar_t__ execute_view (int /*<<< orphan*/ ) ; 
 scalar_t__ parse_query (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_query (struct query*) ; 

HRESULT exec_query( const WCHAR *str, IEnumWbemClassObject **result )
{
    HRESULT hr;
    struct query *query;

    *result = NULL;
    if (!(query = create_query())) return E_OUTOFMEMORY;
    hr = parse_query( str, &query->view, &query->mem );
    if (hr != S_OK) goto done;
    hr = execute_view( query->view );
    if (hr != S_OK) goto done;
    hr = EnumWbemClassObject_create( query, (void **)result );

done:
    release_query( query );
    return hr;
}