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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  HANDLE ;

/* Variables and functions */
 int inject_library_obf (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,char*,int,char*,int,char*,int,char*,int,char*,int) ; 

__attribute__((used)) static inline int inject_library(HANDLE process, const wchar_t *dll)
{
	return inject_library_obf(process, dll, "D|hkqkW`kl{k\\osofj",
				  0xa178ef3655e5ade7, "[uawaRzbhh{tIdkj~~",
				  0x561478dbd824387c, "[fr}pboIe`dlN}",
				  0x395bfbc9833590fd, "\\`zs}gmOzhhBq",
				  0x12897dd89168789a, "GbfkDaezbp~X",
				  0x76aff7238788f7db);
}