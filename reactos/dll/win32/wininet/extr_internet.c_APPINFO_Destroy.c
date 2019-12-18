#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  object_header_t ;
struct TYPE_3__ {int /*<<< orphan*/  proxyPassword; int /*<<< orphan*/  proxyUsername; int /*<<< orphan*/  proxyBypass; int /*<<< orphan*/  proxy; int /*<<< orphan*/  agent; } ;
typedef  TYPE_1__ appinfo_t ;
typedef  int /*<<< orphan*/  VOID ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static VOID APPINFO_Destroy(object_header_t *hdr)
{
    appinfo_t *lpwai = (appinfo_t*)hdr;

    TRACE("%p\n",lpwai);

    heap_free(lpwai->agent);
    heap_free(lpwai->proxy);
    heap_free(lpwai->proxyBypass);
    heap_free(lpwai->proxyUsername);
    heap_free(lpwai->proxyPassword);
}