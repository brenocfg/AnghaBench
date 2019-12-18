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
struct BitField {int* indexes; int /*<<< orphan*/  cIndexes; } ;
typedef  size_t DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 size_t BITS_PER_DWORD ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL CRYPT_IsBitInFieldSet(const struct BitField *field, DWORD bit)
{
    BOOL set;
    DWORD indexIndex = bit / BITS_PER_DWORD;

    assert(field->cIndexes);
    set = field->indexes[indexIndex] & (1 << (bit % BITS_PER_DWORD));
    return set;
}