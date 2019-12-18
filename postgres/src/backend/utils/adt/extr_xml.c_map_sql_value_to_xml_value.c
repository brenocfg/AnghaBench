#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * xmlTextWriterPtr ;
typedef  int /*<<< orphan*/ * xmlBufferPtr ;
struct pg_tm {int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_mon; int /*<<< orphan*/  tm_year; } ;
typedef  int /*<<< orphan*/  int16 ;
typedef  int /*<<< orphan*/  fsec_t ;
typedef  int /*<<< orphan*/  bytea ;
typedef  int /*<<< orphan*/  TimestampTz ;
typedef  int /*<<< orphan*/  Timestamp ;
struct TYPE_9__ {int /*<<< orphan*/  err_occurred; } ;
struct TYPE_8__ {char* data; } ;
typedef  TYPE_1__ StringInfoData ;
typedef  TYPE_2__ PgXmlErrorContext ;
typedef  int Oid ;
typedef  int Datum ;
typedef  scalar_t__ DateADT ;
typedef  int /*<<< orphan*/  ArrayType ;

/* Variables and functions */
 int ARR_ELEMTYPE (int /*<<< orphan*/ *) ; 
#define  BOOLOID 132 
#define  BYTEAOID 131 
#define  DATEOID 130 
 int /*<<< orphan*/  DATE_NOT_FINITE (scalar_t__) ; 
 int /*<<< orphan*/ * DatumGetArrayTypeP (int) ; 
 int /*<<< orphan*/  DatumGetBool (int) ; 
 int /*<<< orphan*/ * DatumGetByteaPP (int) ; 
 scalar_t__ DatumGetDateADT (int) ; 
 int /*<<< orphan*/  DatumGetTimestamp (int) ; 
 int /*<<< orphan*/  ERRCODE_DATETIME_VALUE_OUT_OF_RANGE ; 
 int /*<<< orphan*/  ERRCODE_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  EncodeDateOnly (struct pg_tm*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  EncodeDateTime (struct pg_tm*,int /*<<< orphan*/ ,int,int,char const*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MAXDATELEN ; 
 char* OidOutputFunctionCall (int,int) ; 
 int /*<<< orphan*/  PG_CATCH () ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_RE_THROW () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 int /*<<< orphan*/  PG_XML_STRICTNESS_ALL ; 
 scalar_t__ POSTGRES_EPOCH_JDATE ; 
#define  TIMESTAMPOID 129 
#define  TIMESTAMPTZOID 128 
 int /*<<< orphan*/  TIMESTAMP_NOT_FINITE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USE_XSD_DATES ; 
 int /*<<< orphan*/  VARDATA_ANY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VARSIZE_ANY_EXHDR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XMLBINARY_BASE64 ; 
 int XMLOID ; 
 int /*<<< orphan*/  appendStringInfoString (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  deconstruct_array (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,char,int**,int**,int*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 char* escape_xml (char*) ; 
 int getBaseType (int) ; 
 int /*<<< orphan*/  getTypeOutputInfo (int,int*,int*) ; 
 int /*<<< orphan*/  get_typlenbyvalalign (int,int /*<<< orphan*/ *,int*,char*) ; 
 int /*<<< orphan*/  initStringInfo (TYPE_1__*) ; 
 int /*<<< orphan*/  j2date (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfree (int*) ; 
 int /*<<< orphan*/  pg_xml_done (TYPE_2__*,int) ; 
 TYPE_2__* pg_xml_init (int /*<<< orphan*/ ) ; 
 char* pstrdup (char const*) ; 
 int /*<<< orphan*/  timestamp2tm (int /*<<< orphan*/ ,int*,struct pg_tm*,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ *) ; 
 scalar_t__ type_is_array_domain (int) ; 
 scalar_t__ xmlBufferContent (int /*<<< orphan*/ * volatile) ; 
 int /*<<< orphan*/ * xmlBufferCreate () ; 
 int /*<<< orphan*/  xmlBufferFree (int /*<<< orphan*/ * volatile) ; 
 int /*<<< orphan*/  xmlFreeTextWriter (int /*<<< orphan*/ * volatile) ; 
 int /*<<< orphan*/ * xmlNewTextWriterMemory (int /*<<< orphan*/ * volatile,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlTextWriterWriteBase64 (int /*<<< orphan*/ * volatile,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmlTextWriterWriteBinHex (int /*<<< orphan*/ * volatile,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xml_ereport (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlbinary ; 

char *
map_sql_value_to_xml_value(Datum value, Oid type, bool xml_escape_strings)
{
	if (type_is_array_domain(type))
	{
		ArrayType  *array;
		Oid			elmtype;
		int16		elmlen;
		bool		elmbyval;
		char		elmalign;
		int			num_elems;
		Datum	   *elem_values;
		bool	   *elem_nulls;
		StringInfoData buf;
		int			i;

		array = DatumGetArrayTypeP(value);
		elmtype = ARR_ELEMTYPE(array);
		get_typlenbyvalalign(elmtype, &elmlen, &elmbyval, &elmalign);

		deconstruct_array(array, elmtype,
						  elmlen, elmbyval, elmalign,
						  &elem_values, &elem_nulls,
						  &num_elems);

		initStringInfo(&buf);

		for (i = 0; i < num_elems; i++)
		{
			if (elem_nulls[i])
				continue;
			appendStringInfoString(&buf, "<element>");
			appendStringInfoString(&buf,
								   map_sql_value_to_xml_value(elem_values[i],
															  elmtype, true));
			appendStringInfoString(&buf, "</element>");
		}

		pfree(elem_values);
		pfree(elem_nulls);

		return buf.data;
	}
	else
	{
		Oid			typeOut;
		bool		isvarlena;
		char	   *str;

		/*
		 * Flatten domains; the special-case treatments below should apply to,
		 * eg, domains over boolean not just boolean.
		 */
		type = getBaseType(type);

		/*
		 * Special XSD formatting for some data types
		 */
		switch (type)
		{
			case BOOLOID:
				if (DatumGetBool(value))
					return "true";
				else
					return "false";

			case DATEOID:
				{
					DateADT		date;
					struct pg_tm tm;
					char		buf[MAXDATELEN + 1];

					date = DatumGetDateADT(value);
					/* XSD doesn't support infinite values */
					if (DATE_NOT_FINITE(date))
						ereport(ERROR,
								(errcode(ERRCODE_DATETIME_VALUE_OUT_OF_RANGE),
								 errmsg("date out of range"),
								 errdetail("XML does not support infinite date values.")));
					j2date(date + POSTGRES_EPOCH_JDATE,
						   &(tm.tm_year), &(tm.tm_mon), &(tm.tm_mday));
					EncodeDateOnly(&tm, USE_XSD_DATES, buf);

					return pstrdup(buf);
				}

			case TIMESTAMPOID:
				{
					Timestamp	timestamp;
					struct pg_tm tm;
					fsec_t		fsec;
					char		buf[MAXDATELEN + 1];

					timestamp = DatumGetTimestamp(value);

					/* XSD doesn't support infinite values */
					if (TIMESTAMP_NOT_FINITE(timestamp))
						ereport(ERROR,
								(errcode(ERRCODE_DATETIME_VALUE_OUT_OF_RANGE),
								 errmsg("timestamp out of range"),
								 errdetail("XML does not support infinite timestamp values.")));
					else if (timestamp2tm(timestamp, NULL, &tm, &fsec, NULL, NULL) == 0)
						EncodeDateTime(&tm, fsec, false, 0, NULL, USE_XSD_DATES, buf);
					else
						ereport(ERROR,
								(errcode(ERRCODE_DATETIME_VALUE_OUT_OF_RANGE),
								 errmsg("timestamp out of range")));

					return pstrdup(buf);
				}

			case TIMESTAMPTZOID:
				{
					TimestampTz timestamp;
					struct pg_tm tm;
					int			tz;
					fsec_t		fsec;
					const char *tzn = NULL;
					char		buf[MAXDATELEN + 1];

					timestamp = DatumGetTimestamp(value);

					/* XSD doesn't support infinite values */
					if (TIMESTAMP_NOT_FINITE(timestamp))
						ereport(ERROR,
								(errcode(ERRCODE_DATETIME_VALUE_OUT_OF_RANGE),
								 errmsg("timestamp out of range"),
								 errdetail("XML does not support infinite timestamp values.")));
					else if (timestamp2tm(timestamp, &tz, &tm, &fsec, &tzn, NULL) == 0)
						EncodeDateTime(&tm, fsec, true, tz, tzn, USE_XSD_DATES, buf);
					else
						ereport(ERROR,
								(errcode(ERRCODE_DATETIME_VALUE_OUT_OF_RANGE),
								 errmsg("timestamp out of range")));

					return pstrdup(buf);
				}

#ifdef USE_LIBXML
			case BYTEAOID:
				{
					bytea	   *bstr = DatumGetByteaPP(value);
					PgXmlErrorContext *xmlerrcxt;
					volatile xmlBufferPtr buf = NULL;
					volatile xmlTextWriterPtr writer = NULL;
					char	   *result;

					xmlerrcxt = pg_xml_init(PG_XML_STRICTNESS_ALL);

					PG_TRY();
					{
						buf = xmlBufferCreate();
						if (buf == NULL || xmlerrcxt->err_occurred)
							xml_ereport(xmlerrcxt, ERROR, ERRCODE_OUT_OF_MEMORY,
										"could not allocate xmlBuffer");
						writer = xmlNewTextWriterMemory(buf, 0);
						if (writer == NULL || xmlerrcxt->err_occurred)
							xml_ereport(xmlerrcxt, ERROR, ERRCODE_OUT_OF_MEMORY,
										"could not allocate xmlTextWriter");

						if (xmlbinary == XMLBINARY_BASE64)
							xmlTextWriterWriteBase64(writer, VARDATA_ANY(bstr),
													 0, VARSIZE_ANY_EXHDR(bstr));
						else
							xmlTextWriterWriteBinHex(writer, VARDATA_ANY(bstr),
													 0, VARSIZE_ANY_EXHDR(bstr));

						/* we MUST do this now to flush data out to the buffer */
						xmlFreeTextWriter(writer);
						writer = NULL;

						result = pstrdup((const char *) xmlBufferContent(buf));
					}
					PG_CATCH();
					{
						if (writer)
							xmlFreeTextWriter(writer);
						if (buf)
							xmlBufferFree(buf);

						pg_xml_done(xmlerrcxt, true);

						PG_RE_THROW();
					}
					PG_END_TRY();

					xmlBufferFree(buf);

					pg_xml_done(xmlerrcxt, false);

					return result;
				}
#endif							/* USE_LIBXML */

		}

		/*
		 * otherwise, just use the type's native text representation
		 */
		getTypeOutputInfo(type, &typeOut, &isvarlena);
		str = OidOutputFunctionCall(typeOut, value);

		/* ... exactly as-is for XML, and when escaping is not wanted */
		if (type == XMLOID || !xml_escape_strings)
			return str;

		/* otherwise, translate special characters as needed */
		return escape_xml(str);
	}
}