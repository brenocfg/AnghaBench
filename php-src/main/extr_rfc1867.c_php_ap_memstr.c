__attribute__((used)) static void *php_ap_memstr(char *haystack, int haystacklen, char *needle, int needlen, int partial)
{
	int len = haystacklen;
	char *ptr = haystack;

	/* iterate through first character matches */
	while( (ptr = memchr(ptr, needle[0], len)) ) {

		/* calculate length after match */
		len = haystacklen - (ptr - (char *)haystack);

		/* done if matches up to capacity of buffer */
		if (memcmp(needle, ptr, needlen < len ? needlen : len) == 0 && (partial || len >= needlen)) {
			break;
		}

		/* next character */
		ptr++; len--;
	}

	return ptr;
}