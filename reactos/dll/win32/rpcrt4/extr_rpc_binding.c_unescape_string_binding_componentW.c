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
typedef  char WCHAR ;
typedef  char* RPC_WSTR ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 char* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int strlenW (char const*) ; 

__attribute__((used)) static RPC_WSTR unescape_string_binding_componentW(
    const WCHAR *string_binding, int len)
{
  RPC_WSTR component, p;

  if (len == -1) len = strlenW(string_binding);

  component = HeapAlloc(GetProcessHeap(), 0, (len + 1) * sizeof(*component));
  if (!component) return NULL;
  for (p = component; len > 0; string_binding++, len--) {
    if (*string_binding == '\\') {
      string_binding++;
      len--;
      *p++ = *string_binding;
    } else {
      *p++ = *string_binding;
    }
  }
  *p = '\0';
  return component;
}