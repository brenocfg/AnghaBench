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
typedef  int /*<<< orphan*/  string_table ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  USHORT ;
typedef  int UINT ;

/* Variables and functions */
 int /*<<< orphan*/  MESSAGE (char*,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_wn (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * msi_string_lookup (int /*<<< orphan*/  const*,int /*<<< orphan*/  const,int*) ; 

__attribute__((used)) static void dump_table( const string_table *st, const USHORT *rawdata, UINT rawsize )
{
    UINT i;
    for (i = 0; i < rawsize / 2; i++)
    {
        int len;
        const WCHAR *sval = msi_string_lookup( st, rawdata[i], &len );
        MESSAGE(" %04x %s\n", rawdata[i], debugstr_wn(sval, len) );
    }
}