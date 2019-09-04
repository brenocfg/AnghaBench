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
struct rc4_state {int /*<<< orphan*/  hKey; } ;
typedef  int DWORD ;
typedef  char BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CryptEncrypt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int GetLastError () ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_malloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

void
rdssl_rc4_crypt(void* rc4_info, char* in_data, char* out_data, int len)
{
    struct rc4_state *info = rc4_info;
    BOOL ret;
    DWORD dwErr;
    BYTE * intermediate_data;
    DWORD dwLen = len;
    if (!rc4_info || !in_data || !out_data || !len || !info->hKey)
    {
        error("rdssl_rc4_crypt %p %p %p %d\n", rc4_info, in_data, out_data, len);
        return;
    }
    intermediate_data = g_malloc(len, 0);
    if (!intermediate_data)
    {
        error("rdssl_rc4_set_key no memory\n");
        return;
    }
    memcpy(intermediate_data, in_data, len);
    ret = CryptEncrypt(info->hKey,
                       0,
                       FALSE,
                       0,
                       intermediate_data,
                       &dwLen,
                       dwLen);
    if (!ret)
    {
        dwErr = GetLastError();
        g_free(intermediate_data);
        error("CryptEncrypt failed with %lx\n", dwErr);
        return;
    }
    memcpy(out_data, intermediate_data, len);
    g_free(intermediate_data);
}