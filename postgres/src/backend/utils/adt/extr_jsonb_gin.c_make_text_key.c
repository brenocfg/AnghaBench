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
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/  hashbuf ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int DatumGetUInt32 (int /*<<< orphan*/ ) ; 
 char JGINFLAG_HASHED ; 
 int JGIN_MAXLENGTH ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SET_VARSIZE (int /*<<< orphan*/ *,scalar_t__) ; 
 char* VARDATA (int /*<<< orphan*/ *) ; 
 scalar_t__ VARHDRSZ ; 
 int /*<<< orphan*/  hash_any (unsigned char const*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 scalar_t__ palloc (scalar_t__) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static Datum
make_text_key(char flag, const char *str, int len)
{
	text	   *item;
	char		hashbuf[10];

	if (len > JGIN_MAXLENGTH)
	{
		uint32		hashval;

		hashval = DatumGetUInt32(hash_any((const unsigned char *) str, len));
		snprintf(hashbuf, sizeof(hashbuf), "%08x", hashval);
		str = hashbuf;
		len = 8;
		flag |= JGINFLAG_HASHED;
	}

	/*
	 * Now build the text Datum.  For simplicity we build a 4-byte-header
	 * varlena text Datum here, but we expect it will get converted to short
	 * header format when stored in the index.
	 */
	item = (text *) palloc(VARHDRSZ + len + 1);
	SET_VARSIZE(item, VARHDRSZ + len + 1);

	*VARDATA(item) = flag;

	memcpy(VARDATA(item) + 1, str, len);

	return PointerGetDatum(item);
}