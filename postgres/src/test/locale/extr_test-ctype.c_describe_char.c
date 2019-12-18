void
describe_char(int c)
{
	unsigned char cp = c,
				up = toupper(c),
				lo = tolower(c);

	if (!isprint(cp))
		cp = ' ';
	if (!isprint(up))
		up = ' ';
	if (!isprint(lo))
		lo = ' ';

	printf("chr#%-4d%2c%6s%6s%6s%6s%6s%6s%6s%6s%6s%6s%6s%4c%4c\n", c, cp, flag(isalnum(c)), flag(isalpha(c)), flag(iscntrl(c)), flag(isdigit(c)), flag(islower(c)), flag(isgraph(c)), flag(isprint(c)), flag(ispunct(c)), flag(isspace(c)), flag(isupper(c)), flag(isxdigit(c)), lo, up);
}