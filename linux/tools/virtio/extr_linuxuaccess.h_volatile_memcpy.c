__attribute__((used)) static void volatile_memcpy(volatile char *to, const volatile char *from, 
			    unsigned long n)
{
	while (n--)
		*(to++) = *(from++);
}