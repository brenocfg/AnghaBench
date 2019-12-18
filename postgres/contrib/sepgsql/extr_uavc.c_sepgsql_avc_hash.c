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
typedef  int uint32 ;
typedef  int uint16 ;

/* Variables and functions */
 int hash_any (unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static uint32
sepgsql_avc_hash(const char *scontext, const char *tcontext, uint16 tclass)
{
	return hash_any((const unsigned char *) scontext, strlen(scontext))
		^ hash_any((const unsigned char *) tcontext, strlen(tcontext))
		^ tclass;
}