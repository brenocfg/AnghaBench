#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  text ;
struct TYPE_3__ {scalar_t__ name; int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ priv_map ;
typedef  int /*<<< orphan*/  AclMode ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_INVALID_PARAMETER_VALUE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*) ; 
 scalar_t__ isspace (unsigned char) ; 
 int /*<<< orphan*/  pfree (char*) ; 
 scalar_t__ pg_strcasecmp (scalar_t__,char*) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 char* text_to_cstring (int /*<<< orphan*/ *) ; 

__attribute__((used)) static AclMode
convert_any_priv_string(text *priv_type_text,
						const priv_map *privileges)
{
	AclMode		result = 0;
	char	   *priv_type = text_to_cstring(priv_type_text);
	char	   *chunk;
	char	   *next_chunk;

	/* We rely on priv_type being a private, modifiable string */
	for (chunk = priv_type; chunk; chunk = next_chunk)
	{
		int			chunk_len;
		const priv_map *this_priv;

		/* Split string at commas */
		next_chunk = strchr(chunk, ',');
		if (next_chunk)
			*next_chunk++ = '\0';

		/* Drop leading/trailing whitespace in this chunk */
		while (*chunk && isspace((unsigned char) *chunk))
			chunk++;
		chunk_len = strlen(chunk);
		while (chunk_len > 0 && isspace((unsigned char) chunk[chunk_len - 1]))
			chunk_len--;
		chunk[chunk_len] = '\0';

		/* Match to the privileges list */
		for (this_priv = privileges; this_priv->name; this_priv++)
		{
			if (pg_strcasecmp(this_priv->name, chunk) == 0)
			{
				result |= this_priv->value;
				break;
			}
		}
		if (!this_priv->name)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_PARAMETER_VALUE),
					 errmsg("unrecognized privilege type: \"%s\"", chunk)));
	}

	pfree(priv_type);
	return result;
}