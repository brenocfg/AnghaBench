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
typedef  scalar_t__ int32 ;
typedef  int Oid ;

/* Variables and functions */
#define  BITOID 132 
 scalar_t__ BITS_PER_BYTE ; 
#define  BPCHAROID 131 
 int /*<<< orphan*/  GetDatabaseEncoding () ; 
#define  NUMERICOID 130 
#define  VARBITOID 129 
#define  VARCHAROID 128 
 scalar_t__ VARHDRSZ ; 
 scalar_t__ numeric_maximum_size (scalar_t__) ; 
 scalar_t__ pg_encoding_max_length (int /*<<< orphan*/ ) ; 

int32
type_maximum_size(Oid type_oid, int32 typemod)
{
	if (typemod < 0)
		return -1;

	switch (type_oid)
	{
		case BPCHAROID:
		case VARCHAROID:
			/* typemod includes varlena header */

			/* typemod is in characters not bytes */
			return (typemod - VARHDRSZ) *
				pg_encoding_max_length(GetDatabaseEncoding())
				+ VARHDRSZ;

		case NUMERICOID:
			return numeric_maximum_size(typemod);

		case VARBITOID:
		case BITOID:
			/* typemod is the (max) number of bits */
			return (typemod + (BITS_PER_BYTE - 1)) / BITS_PER_BYTE
				+ 2 * sizeof(int32);
	}

	/* Unknown type, or unlimited-width type such as 'text' */
	return -1;
}