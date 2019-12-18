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

/* Variables and functions */
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 int /*<<< orphan*/  FreeLibrary (scalar_t__) ; 
 int /*<<< orphan*/  IMultiLanguage2_Release (scalar_t__) ; 
 scalar_t__ TLS_OUT_OF_INDEXES ; 
 int /*<<< orphan*/  TlsFree (scalar_t__) ; 
 int /*<<< orphan*/  close_gecko () ; 
 scalar_t__ display_dc ; 
 int /*<<< orphan*/  free_strings () ; 
 scalar_t__ mlang ; 
 scalar_t__ mshtml_tls ; 
 int /*<<< orphan*/  release_typelib () ; 
 scalar_t__ shdoclc ; 

__attribute__((used)) static void process_detach(void)
{
    close_gecko();
    release_typelib();

    if(shdoclc)
        FreeLibrary(shdoclc);
    if(mshtml_tls != TLS_OUT_OF_INDEXES)
        TlsFree(mshtml_tls);
    if(display_dc)
        DeleteObject(display_dc);
    if(mlang)
        IMultiLanguage2_Release(mlang);

    free_strings();
}